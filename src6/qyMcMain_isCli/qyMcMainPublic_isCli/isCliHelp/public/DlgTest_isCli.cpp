// DlgTest.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"myresource.h"

#include	"DlgTest_isCli.h"
#include	"afxdialogex.h"

#include	"qmcVideoCapture.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
//  #include	"DlgDynBmps.h"

#include	"qmcVideoCapture.h"
//  #include	"DlgCfgVideoConference.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"

#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )  
	//  #include	"DlgQnmSendHint.h"
	//  #include	"dlgSelect_isCli.h"
	#include	"qyPs.h"
	//  #include	"dlgQyBar.h"			//  2012/04/10
#endif

#include	"dlgTalkProc.h"
//  #include	"DlgVideos.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"
//  #include	"DlgMsgList.h"
#include	"qmcGpsProc.h"

#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

 __declspec(  dllexport  )  int  testLocalAv(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	MIS_CNT				*	pMisCnt		=		getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	//
#ifndef  __NOTSUPPORT_testLocalAv__
	//  CDlgDynBmps			*	pDlg		=		NULL;
	CDlgTest_isCli			*	pDlg			=		NULL;
	CWaitCursor				cur;
#endif

	traceLogA(  "testLocalWebcam enters"  );

	if  (  IsWindow(  pProcInfo->hWnd_testWebcam  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->hWnd_testWebcam  );
		return  0;
	}

	//
#ifndef  __NOTSUPPORT_testLocalAv__
	{
		RECT					rect;
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		/*
		unsigned  int		uiInitW				=	pVar->av.localAv.videoCaptureProcInfo.vh_org.bih.biWidth;
		unsigned  int		uiInitH				=	pVar->av.localAv.videoCaptureProcInfo.vh_org.bih.biHeight;
		//
		if  (  uiInitH  <  300  )  {
			uiInitW  =  (  unsigned  int  )(  uiInitW  /  (  uiInitH  *  1.  )  *  300.  );
			uiInitH  =  300;
		}
		*/
		unsigned  int  uiInitW  =  640  +  30;
		unsigned  int  uiInitH  =  480  +  30;
		//  2013/03/06
		int  iResId_menu  =  CONST_resId_menu_dlgTest;
		//
		//  pDlg  =  new  CDlgTestWebcam(  CWnd::GetDesktopWindow(  )  );
		CWnd  *  pParent  =  CWnd::GetDesktopWindow(  );
		pParent  =  CWnd::FromHandle(  hParent  );
		pDlg  =  new  CDlgTest_isCli(  pParent  );	//  CDlgDynBmps(  pParent  );
		if  (  !pDlg  )  goto  errLabel;
		if  (  !pDlg->bSetDlgInfo(  CONST_qyWndContentType_testLocalAv,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localVideo  ),  iResId_menu  )  )  goto  errLabel;

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		pDlg->ShowWindow(  SW_SHOW  );
		//
		pProcInfo->hWnd_testWebcam  =  pDlg->m_hWnd;
		
		pDlg  =  NULL;
	}
#endif

	//

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
#ifndef  __NOTSUPPORT_testLocalAv__
		if  (  pDlg  )  delete  pDlg;
#endif
	}

	traceLogA(  "testLocalWebcam leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}


// CDlgTest_isCli dialog

IMPLEMENT_DYNAMIC(CDlgTest_isCli, CDialog)

CDlgTest_isCli::CDlgTest_isCli(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest_isCli::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgTest_isCli::IDD;

	//
	m_var.guiData.iIDC_STATIC_pic0  =  IDC_STATIC_pic0;

	m_var.guiData.iIDC_STATIC_testAvHint  =  IDC_STATIC_testAvHint;
	
	m_var.guiData.iIDC_BUTTON_aDev  =  IDC_BUTTON_aDev;
	m_var.guiData.iIDC_STATIC_aDev  =  IDC_STATIC_aDev;
	
	m_var.guiData.iIDC_BUTTON_vDev  =  IDC_BUTTON_vDev;
	m_var.guiData.iIDC_STATIC_vDev  =  IDC_STATIC_vDev;
	
	m_var.guiData.iIDC_BUTTON_cfgCapturePin_v  =  IDC_BUTTON_cfgCapturePin_v;

	m_var.guiData.iIDC_BUTTON_testAv  =  IDC_BUTTON_testAv;
	
	m_var.guiData.iIDCANCEL  =  IDCANCEL;

	

	//  2013/03/19
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	m_var.bIncludeAudio  =  pProcInfo->cfg.policy.audio.uiRecordType  ==  CONST_recordType_directX;	

}

CDlgTest_isCli::~CDlgTest_isCli()
{
}


BOOL  CDlgTest_isCli::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu  )
{
	BOOL		bRet  =  FALSE;

	m_var.iWndContentType  =  iWndContentType;
	safeTcsnCpy(  title,  m_var.title,  mycountof(  m_var.title  )  );
	m_var.iResId_menu  =  iResId_menu;
	bRet  =  TRUE;

	return  bRet;
}

BOOL CDlgTest_isCli::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): ÔÚ´´½¨¶Ô»°¿òÖ®Ç°Ó¦ÏÈÉèÖÃ³õÊ¼Êý¾Ý"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgTest_isCli::bQuitDlg(  )		
{		
	BOOL		bRet	=	FALSE;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	DestroyWindow(  );

	bRet  =  TRUE;
	return  bRet;
 }

  int  CDlgTest_isCli::sizeAllControls(  )
{

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	DLG_guiData_test_isCli  *  p  =  &m_var.guiData;
	HWND						hDlg	=	m_hWnd;
	
	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->iw_org;
	fy  =  1.  *  h  /  p->ih_org;

		
	idc  =  p->iIDC_STATIC_pic0;	
	rc  =  p->rcIDC_STATIC_pic0;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
			
	idc  =  p->iIDC_STATIC_testAvHint;
	rc  =  p->rcIDC_STATIC_testAvHint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_aDev;	
	rc  =  p->rcIDC_BUTTON_aDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		
	idc  =  p->iIDC_STATIC_aDev;	
	rc  =  p->rcIDC_STATIC_aDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
	
	idc  =  p->iIDC_BUTTON_vDev;	
	rc  =  p->rcIDC_BUTTON_vDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_vDev;	
	rc  =  p->rcIDC_STATIC_vDev;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
		

	idc  =  p->iIDC_BUTTON_cfgCapturePin_v;	
	rc  =  p->rcIDC_BUTTON_cfgCapturePin_v;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	idc  =  p->iIDC_BUTTON_testAv;	
	rc  =  p->rcIDC_BUTTON_testAv;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  
	
	idc  =  p->iIDCANCEL;	
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  ::GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	//
	CWnd  *  pCtrl;

	pCtrl  =  GetDlgItem(  m_var.idc  );
	if  (  !pCtrl  )  goto  errLabel;
	pCtrl->Invalidate(  TRUE  );
	//  pCtrl->UpdateWindow(  );

	pCtrl->GetClientRect(  &rc  );

	m_var.iW_pic  =  rc.right  -  rc.left;
	m_var.iH_pic  =  rc.bottom  -  rc.top;

	getCapImages(  0,  0,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  &m_var.images  );

errLabel:
	return  0;
}

void CDlgTest_isCli::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTest_isCli, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_aDev, &CDlgTest_isCli::OnBnClickedButtonadev)
	ON_BN_CLICKED(IDC_BUTTON_vDev, &CDlgTest_isCli::OnBnClickedButtonvdev)
	ON_BN_CLICKED(IDC_BUTTON_cfgCapturePin_v, &CDlgTest_isCli::OnBnClickedButtoncfgcapturepinv)
	ON_BN_CLICKED(IDC_BUTTON_testAv, &CDlgTest_isCli::OnBnClickedButtontestav)
	ON_WM_DESTROY()
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
	ON_WM_SIZE()
	ON_COMMAND_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnIsCmd  )
	ON_UPDATE_COMMAND_UI_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnUpdateIsCmd  )
END_MESSAGE_MAP()


// CDlgTest_isCli message handlers


BOOL CDlgTest_isCli::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//
	int						iErr				=	-1;
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs				=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  goto  errLabel;


	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );	
	if  (  !pResMem  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	RECT	rc;

	::GetClientRect(  m_hWnd,  &rc  );

	DLG_guiData_test_isCli  *  p  =  &m_var.guiData;

	p->iw_org  =  rc.right  -  rc.left;  
	p->ih_org  =  rc.bottom  -  rc.top;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_pic0  ),  &p->rcIDC_STATIC_pic0  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_pic0,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_testAvHint  ),  &p->rcIDC_STATIC_testAvHint  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_testAvHint,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_aDev  ),  &p->rcIDC_BUTTON_aDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_aDev,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_aDev  ),  &p->rcIDC_STATIC_aDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_aDev,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_vDev  ),  &p->rcIDC_BUTTON_vDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_vDev,  2  );
	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_STATIC_vDev  ),  &p->rcIDC_STATIC_vDev  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_STATIC_vDev,  2  );
		
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_cfgCapturePin_v  ),  &p->rcIDC_BUTTON_cfgCapturePin_v  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_cfgCapturePin_v,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_testAv  ),  &p->rcIDC_BUTTON_testAv  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_testAv,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDCANCEL,  2  );
	

	//  m_var.iResId_menu  =

	if  (  m_var.iResId_menu  )  {		
		CMenu			*	pMenu	=	this->GetMenu(  );
		QY_DMITEM		*	pItem;
		unsigned  int		nPos	=	m_var.iResId_menu;		//  CONST_resId_menu_dlgVideos;

		if  (  !pMenu  )  goto  errLabel;
#if  1  //  def  __SUPPORT_wndMenu__
		if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "CDlgDesktopsMon::OnInitDialog failed, pItem CONST_resId_popupMenu is null"  )  );
			#endif
			goto  errLabel;
		}
		if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "DlgDesktopsMon::OnInitDialog: qyGetDmItemByType failed, nPos %d"  ),  nPos  );
			#endif
			goto  errLabel;
		}
		if  (	 makeDynaMenu(  &pQyMc->cusRes,  pMenu->m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  0,  0  )  )  goto  errLabel;		
#endif

	}


#ifdef  __APP_qyMc_touchscreen__
	{
		RECT	rc;
		int		w, h;
		HWND	hFrame	=	pQyMc->gui.hMainWnd;
		if  (  !hFrame  )  goto  errLabel;
		::GetWindowRect(  hFrame,  &rc  );
		w  =  rc.right  -  rc.left;
		h  =  rc.bottom  -  rc.top;
		::MoveWindow(  m_hWnd,  rc.left,  rc.top,  w,  h,  TRUE  );		
	}
#endif


	//
	m_var.idc  =  IDC_STATIC_pic0;

	sizeAllControls(  );

	//
	m_var.pCapStuff  =  pFuncs->pf_CAP_STUFF_new(  );		//  2009/09/16		
	if  (  !m_var.pCapStuff  )  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(  m_var.pCapStuff,  m_var.bIncludeAudio,  NULL  );		
	//
	TCHAR	recorder_sel[MAX_monikerDisplayNameLen  +  1]  =  _T(  ""  );		
	TCHAR	webcam_sel[MAX_monikerDisplayNameLen  +  1]	=  _T(  ""  );
	pFuncs->pf_getChosenDevice(  recorder_sel,  mycountof(  recorder_sel  ),  webcam_sel,  mycountof(  webcam_sel  ),  m_var.pCapStuff,  m_var.bIncludeAudio,  &m_var.iMenuId_selectedAudio,  &m_var.iMenuId_selectedVideo  );  
	if  (  !m_var.iMenuId_selectedAudio  )  {	
		m_var.iMenuId_selectedAudio  =  ID_MENU_ADEVICE0;
	}
	if  (  !m_var.iMenuId_selectedVideo  )  {	
		m_var.iMenuId_selectedVideo  =  ID_MENU_VDEVICE0;		 
	}

	//
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	int  index  =  m_var.iMenuId_selectedVideo  -  ID_MENU_VDEVICE0;
	if  (  index  <  0  ||  index  >=  mycountof(  pCapStuff->rgpmVideoMenu  )  )  goto  errLabel;
	//  ChooseDevices(  *pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );
	pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );

	//
	TCHAR	tBuf[256]  =  _T(  ""  );
	pFuncs->moniker.pf_getADevFriendlyName(  m_var.pCapStuff,  m_var.bIncludeAudio,  m_var.iMenuId_selectedAudio,  tBuf,  mycountof(  tBuf  )  );
	SetDlgItemText(  IDC_STATIC_aDev,  tBuf  );
	tBuf[0]  =  0;
	//  getMonikerFriendlyName(  getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  tBuf,  mycountof(  tBuf  )  );
	pFuncs->moniker.pf_getMonikerProp(  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  CONST_moniker_FriendlyName,  tBuf,  mycountof(  tBuf  )  );
	SetDlgItemText(  IDC_STATIC_vDev,  tBuf  );

	//
	m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )malloc(  sizeof(  MIS_MSGU  )  );	
	if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;


	SetWindowText(  m_var.title  );
	//
	SetDlgItemText(  m_var.guiData.iIDC_STATIC_testAvHint,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_testAvHint  )  );

	//
	m_var.bInited  =  TRUE;

	//
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTest_isCli::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	//
	if  (  m_var.bCreated  )  {

		traceLogA(  "CDlgTest_isCli::PostNcDestroy(  ): delete this"  );
		try  {
			 delete  this;		
			}
		catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTest_isCli::PostNcDestroy failed."  )  );
		}

	}

	qisApplyForChkingTasks_gui(  );	//  2009/09/10

}


void CDlgTest_isCli::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();
	bQuitDlg(  );
}


void CDlgTest_isCli::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}



void CDlgTest_isCli::OnBnClickedButtonadev()
{
	// TODO: Add your control notification handler code here
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;
	DLG_guiDataParam_objs		param;
	
	memset(  &param,  0,  sizeof(  param  )  );	
	param.uiType  =  CONST_objType_selectADev;
	param.p0  =  m_var.pCapStuff;
	param.iMenuId_selectedDev  =  m_var.iMenuId_selectedAudio;
				  		
	if  (  showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  goto  errLabel;
		
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	//
	if  (  param.o.iSel  <  0  ||  param.o.iSel  >=  mycountof(  pCapStuff->old_audioDevices.mems  )  )  goto  errLabel;

	int  iMenuId  =  pCapStuff->old_audioDevices.mems[param.o.iSel].iMenuIds_audio;

	if  (  iMenuId  !=  m_var.iMenuId_selectedAudio  )  {


		if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
			m_var.iMenuId_selectedAudio  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeAudio,  iMenuId  );
			//  getChosenDevice(  pProcInfo->av.localAv.recorder_selected,  mycountof(  pProcInfo->av.localAv.recorder_selected  ),  NULL,  0  );
		}
		if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
			m_var.iMenuId_selectedVideo  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeAudio,  iMenuId  );
			//  getChosenDevice(  NULL,  0,  pProcInfo->av.localAv.webcam_selected,  mycountof(  pProcInfo->av.localAv.webcam_selected  )  );
		}

		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		pFuncs->moniker.pf_getADevFriendlyName(  m_var.pCapStuff,  m_var.bIncludeAudio,  m_var.iMenuId_selectedAudio,  tBuf,  mycountof(  tBuf  )  );
		SetDlgItemText(  IDC_STATIC_aDev,  tBuf  );

	}

errLabel:
	return;
}


void CDlgTest_isCli::OnBnClickedButtonvdev()
{
	// TODO: Add your control notification handler code here
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;
	DLG_guiDataParam_objs		param;
	
	memset(  &param,  0,  sizeof(  param  )  );	
	param.uiType  =  CONST_objType_selectVDev;
	param.p0  =  m_var.pCapStuff;
	param.iMenuId_selectedDev  =  m_var.iMenuId_selectedVideo;
				  		
	if  (  showDlgObjs(  pQyMc->g_hInst,  m_hWnd,  &param  )  )  goto  errLabel;
	
	CAP_STUFF  *  pCapStuff  =  (  CAP_STUFF  *  )m_var.pCapStuff;
	//
	if  (  param.o.iSel  <  0  ||  param.o.iSel  >=  mycountof(  pCapStuff->rgpmVideoMenu  )  )  goto  errLabel;

	int  iMenuId  =  ID_MENU_VDEVICE0  +  param.o.iSel;

	if  (  iMenuId  !=  m_var.iMenuId_selectedVideo  )  {

		//
		pFuncs->pf_myChooseDevices(  pCapStuff,  pCapStuff->rgpmVideoMenu[param.o.iSel],  pCapStuff->pmAudio  );

		//
		if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
			m_var.iMenuId_selectedAudio  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeAudio,  iMenuId  );
			//  getChosenDevice(  pProcInfo->av.localAv.recorder_selected,  mycountof(  pProcInfo->av.localAv.recorder_selected  ),  NULL,  0  );
		}
		if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
			m_var.iMenuId_selectedVideo  =  iMenuId;
			pFuncs->pf_saveChosenDevice(  m_var.pCapStuff,  m_var.bIncludeAudio,  iMenuId  );
			//  getChosenDevice(  NULL,  0,  pProcInfo->av.localAv.webcam_selected,  mycountof(  pProcInfo->av.localAv.webcam_selected  )  );
		}

		//
		TCHAR  tBuf[256]  =  _T(  ""  );
		//  getMonikerFriendlyName(  getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  tBuf,  mycountof(  tBuf  )  );
		pFuncs->moniker.pf_getMonikerProp(  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  CONST_moniker_FriendlyName,  tBuf,  mycountof(  tBuf  )  );
		SetDlgItemText(  IDC_STATIC_vDev,  tBuf  );

	}

errLabel:
	return;
}

void CDlgTest_isCli::OnBnClickedButtoncfgcapturepinv()
{
	// TODO: Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	pFuncs->pf_cfgCapturePin(  m_var.pCapStuff,  this->m_hWnd  );
}


void CDlgTest_isCli::OnBnClickedButtontestav()
{
	// TODO: Add your control notification handler code here
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;
		
	//  2013/03/19
	TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]  =  _T(  ""  );
	if  (  m_var.bIncludeAudio  )  {
		pFuncs->moniker.pf_getMonikerDisplayName(  pFuncs->moniker.pf_getMoniker_a(  m_var.pCapStuff,  m_var.iMenuId_selectedAudio  ),  displayName,  mycountof(  displayName  )  );
	}
	TCHAR  capDevDesc[64]  =  _T(  ""  );
	void  *  pADev  =  m_var.bIncludeAudio  ?    displayName  :  pFuncs->moniker.pf_getADeviceGuid(  m_var.pCapStuff,  m_var.iMenuId_selectedAudio,  capDevDesc, mycountof(  capDevDesc  )  );
	if  (  pFuncs->pf_testLocalAv_openLocalVideo(  this->m_hWnd,  pADev,  capDevDesc,  pFuncs->moniker.pf_getMoniker_v(  m_var.pCapStuff,  m_var.iMenuId_selectedVideo  ),  &m_var.bGot_sharedObjIndex_localAv,  &m_var.iIndex_sharedObj_localAv  )  )  {
					  //  goto  errLabel;
	
	}

	//  只操作一次
	GetDlgItem(  IDC_BUTTON_testAv  )->EnableWindow(  FALSE  );
}


void CDlgTest_isCli::OnDestroy()
{
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	MACRO_qyAssert(  pFuncs,  _T(  "FUNCS err"  )  );
	
	//
	if  (  m_var.bGot_sharedObjIndex_localAv  )  {
		pFuncs->pf_freeSharedObjUsr_localAv(  m_var.iIndex_sharedObj_localAv,  this->m_hWnd  );				  
	}				  
	//	
	pFuncs->pf_stopLocalAudioPlaying(  );


	//	
	MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );		//  2009/12/10

	//
	int  idc_dst  =  m_var.idc;
	freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc  );
	
	//
	pFuncs->pf_CAP_STUFF_free(  m_var.pCapStuff  );		//  2009/09/16


	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}


 LRESULT  CDlgTest_isCli::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	//  int					iWndContentType		=					getWndContentType(  );
	MC_VAR_isCli		*	pProcInfo			=				QY_GET_procInfo_isCli(  );	//  	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				  MIS_MSG_procVideo_qmc		*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )pComm;
				  BOOL							bUseDxSurface	=	FALSE;	//  m_var.bUseDirectX;
				
#ifdef  __DEBUG__
	    //  bUseDxSurface  =  FALSE;
#endif

					  //  2011/11/27. 在全高清视频时，在笔记本上显示不了了，不能使用dx.
					  bUseDxSurface  =  FALSE;

					  //
					  if  (  drawCapImages(  this->m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  FALSE,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  NULL,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;

				  }
												   
				  break;
			default:
					break;
	}

		lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
 }


  LRESULT  CDlgTest_isCli::OnQyPostComm( WPARAM wParam, LPARAM lParam )
{
	long				lRet			=		-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  this->m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
			default:
					break;
	}
	
	lRet  =  QY_RC_WMOK;
	
errLabel:

	return  lRet;

  }

  void CDlgTest_isCli::OnSize(UINT nType, int cx, int cy)
  {
	  CDialog::OnSize(nType, cx, cy);

	  // TODO: Add your message handler code here
	sizeAllControls(  );
  }

 
  void CDlgTest_isCli::OnIsCmd(  UINT iMenuId  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;
	
	//  2013/02/06
	if  (  iMenuId  >=  ID_dlgTest_min  &&  iMenuId  <=  ID_dlgTest_max  )  {
		pFuncs->pf_doCmd_test(  iMenuId  );
		iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;
	errLabel:
	return;
  }


  void CDlgTest_isCli::OnUpdateIsCmd(CCmdUI *pCmdUI)
{
}


